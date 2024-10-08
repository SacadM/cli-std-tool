#ifndef AREAS_H
#define AREAS_H

/*
  +---------------------------------------+
  | BETH YW? WELSH GOVERNMENT DATA PARSER |
  +---------------------------------------+

  AUTHOR: <Sacad Muhumed>

  This file contains the Areas class, which is responsible for parsing data
  from a standard input stream and converting it into a series of objects:

  Measure       — Represents a single measure for an area, e.g.
   |              population. Contains a human-readable label and a map of
   |              the measure accross a number of years.
   |
   +-> Area       Represents an area. Contains a unique local authority code
        |         used in national statistics, a map of the names of the area 
        |         (i.e. in English and Welsh), and a map of various Measure 
        |         objects.
        |
        +-> Areas A class that contains all Area objects.
 */

#include <iostream>
#include <string>
#include <tuple>
#include <unordered_set>

#include "datasets.h"
#include "area.h"

/*
  An alias for filters based on strings such as categorisations e.g. area,
  and measures.
*/
using StringFilterSet = std::unordered_set<std::string>;

/*
  An alias for a year filter.
*/
using YearFilterTuple = std::tuple<unsigned int, unsigned int>;

/*
  An alias for the data within an Areas object stores Area objects.
*/
class Null { };
using AreasContainer = Null;

/*
  Areas is a class that stores all the data categorised by area.
*/
class Areas {
private:
  std::map<std::string, Area> areas;
public:
  Areas();
  
  void populateFromAuthorityCodeCSV(
      std::istream& is,
      const BethYw::SourceColumnMapping& cols,
      const StringFilterSet * const areas = nullptr)
      noexcept(false);

  void populate(
      std::istream& is,
      const BethYw::SourceDataType& type,
      const BethYw::SourceColumnMapping& cols) noexcept(false);

  void populate(
      std::istream& is,
      const BethYw::SourceDataType& type,
      const BethYw::SourceColumnMapping& cols,
      const StringFilterSet * const areasFilter = nullptr,
      const StringFilterSet * const measuresFilter = nullptr,
      const YearFilterTuple * const yearsFilter = nullptr)
      noexcept(false);

  std::string toJSON() const;

  void insertArea(const Area& area);

  void populateFromWelshStatsJSON(std::istream &is,
                                       const BethYw::SourceColumnMapping &cols,
                                       const StringFilterSet * const areasFilter,
                                       const StringFilterSet * const measuresFilter,
                                       const YearFilterTuple * const yearsFilter);

  void populateFromAuthorityByYearCSV(std::istream &is,
                                      const BethYw::SourceColumnMapping &cols,
                                      const StringFilterSet *const areasFilter,
                                      const StringFilterSet *const measuresFilter,
                                      const YearFilterTuple *const yearsFilter);
  
  void setArea(const std::string &localAuthorityCode, Area area);

  Area& getArea(const std::string& localAuthorityCode);

  std::size_t size() const;
  friend std::ostream& operator<<(std::ostream& os, const Areas& _areas);
};

#endif // AREAS_H