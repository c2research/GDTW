#ifndef GDTW_ONLINE_H
#define GDTW_ONLINE_H

#include <vector>
#include <string>

#include "TimeSeriesSet.hpp"

/**
 * A struct holding general information of a dataset
 */
struct dataset_info_t
{
  dataset_info_t() : name(""), id(-1), itemCount(0), itemLength(0) {}
  dataset_info_t(int id, std::string name, int itemCount, int itemLength) :
    name(name), id(id), itemCount(itemCount), itemLength(itemLength) {}

  std::string name;
  int id;
  int itemCount;
  int itemLength;
};

/**
 * A struct holding general information of a distance metric
 */
struct distance_info_t
{
  distance_info_t(std::string name, std::string description) :
    name(name), description(description) {}
  std::string name;
  std::string description;
};

/**
 *  @brief a struct pairing a dist with a time series
 *
 */
struct candidate_time_series_t
{
  TimeSeries data;
  data_t dist;

  candidate_time_series_t(const TimeSeries &data, data_t dist) : data(data), dist(dist){};
};

class GDTWOnline
{
public:

  /**
   *  @brief destructor
   */
  ~GDTWOnline();

  /**
   *  @brief loads data from a text file to the memory
   *
   *  Values in the text file have to be arranged in a table format. The number of
   *  values (a.k.a columns) is inferred from the first line. All lines must have
   *  the same number of columns. If the number of lines exceeds maxNumRow, only
   *  maxNumRow lines are read and the rest is discarded. On the other hand, if
   *  maxNumRow is larger than or equal to the actual number of lines, or maxNumRow is
   *  not positive all lines are read.
   *
   *  @param filePath path to a text file
   *  @param maxNumRow maximum number of rows to be read. If this value is not positive,
   *         all lines are read
   *  @param separator a string containings possible separator characters for values
   *         in a line
   *  @param startCol columns before startCol are discarded
   *  @return an index used to refer to the just loaded dataset
   *
   *  @throw GenexException if cannot read from the given file
   */
  dataset_info_t loadDataset(const std::string& filePath, int maxNumRow,
                             int startCol, const std::string& separators);

  /**
   *  @brief unloads a dataset at given index
   *
   *  @param index index of the dataset being unloaded
   */
  void unloadDataset(int index);

  /**
   *  @brief unloads all datasets
   */
  void unloadAllDataset();

  /**
   *  @return number of loaded datasets
   */
  int getDatasetCount();

  /**
   *  @brief gets information of a dataset
   *
   *  @param index index of the dataset
   *  @return a dataset_info_t struct containing information about the dataset
   */
  dataset_info_t getDatasetInfo(int index);

  /**
   *  @return a vector of information of loaded dataset
   */
  std::vector<dataset_info_t> getAllDatasetInfo();

  /**
   *  @return a vector of names of available distance metrics
   */
  std::vector<distance_info_t> getAllDistanceInfo();

  /**
   *  @brief Gets the distance between two time series
   */
  data_t getDistanceBetween(int index1, int idx1, int start1, int length1,
                            int index2, int idx2, int start2, int length2,
                            const std::string& distance);

  /**
   *  Set a file where the DTW path will be print to. Nothing will print
   *  if set this path to an empty string.
   */
  void setPrintDTWPathToFile(const std::string& path);

  /**
   *  @brief Finds the nearest time series using gdtw
   */
  candidate_time_series_t getBestMatchRaw(
      int index1, int idx1, int start1, int length1,
      int index2, const std::string &distance_name);

private:
  void _checkDatasetIndex(int index);

  std::string dtwPathFile = "";
  std::vector<TimeSeriesSet*> loadedDatasets;
  int datasetCount = 0;
};

#endif // GDTW_ONLINE_H