#ifndef TIMESERIESSET_H
#define TIMESERIESSET_H

#include <string>
#include <vector>

#include "TimeSeries.hpp"
#include "distance/Distance.hpp"

/**
 *  @brief a TimeSeriesSet object contains values and information of a dataset
 *
 *  Example:
 *    TimeSeriesSet dataset("example")
 *    dataset.load("data.txt", 20);
 */
class TimeSeriesSet
{
public:

  /**
   *  @brief default constructor for TimeSeriesSet
   *
   *  Create a TimeSeriestSet object with is an empty string for name
   */
  TimeSeriesSet()
    : itemLength(0), itemCount(0) {};

  /**
   *  @brief destructor
   */
  virtual ~TimeSeriesSet();

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
   *  @param startCol columns before startCol are discarded
   *  @param separator a string containings possible separator characters for values
   *         in a line
   *
   *  @throw GenexException if cannot read from the given file
   */
  void loadData(const std::string& filePath, int maxNumRow, int startCol, const std::string& separator);

  /**
   * @brief clears all data
   */
  void clearData();

  /**
   * @brief gets length of each time series in the dataset
   *
   * @return length of each time series
   */
  int getItemLength() const { return this->itemLength; }

  /**
   * @brief gets number of time series in the dataset
   *
   * @return number of time series
   */
  int getItemCount() const { return this->itemCount; }

  /**
   * @brief gets the file path of the dataset
   *
   * @return file path of the dataset
   */
  const std::string& getFilePath() const { return this->filePath; }

  /**
   * @brief gets a whole time series
   *
   * @param index index of the time series in this dataset
   * @return time series in the time series with given index
   */
  TimeSeries getTimeSeries(int index) const;

  /**
   * @brief gets a sub-sequence of a time series
   *
   * @param index index of the time series in this dataset
   * @param start starting position of the time series
   * @param end   ending position of the time series
   * @return a sub-sequence of a time series in the dataset
   *
   * @throw GenexException if index, start or end is not in intended range
   */
  TimeSeries getTimeSeries(int index, int start, int end) const;

  /**
   *  @brief normalizes the timeseries set
   *
   *  @return the min and max of the dataset
   *  @throws exception when there is no data in the set
   */
  std::pair<data_t, data_t> normalize();

  /**
   *  @brief a set is valid if it contains data (valid for grouping)
   */
  bool valid(void);

protected:
  data_t* data = nullptr;
  int itemLength;
  int itemCount;

private:
  std::string filePath;

};


#endif // TIMESERIESSET_H
