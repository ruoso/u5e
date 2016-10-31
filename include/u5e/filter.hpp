#ifndef INCLUDED_U5E_FILTER
#define INCLUDED_U5E_FILTER

namespace u5e {

  /**
   * \brief Walks an input iterator through a filter
   *
   * This will go from the begin to the end of the input iterator and
   * will execute the filter function once for every input element.
   *
   * Unlike std::transform, the filter function does not return the
   * output element, but it receives the output object and will do
   * whatever makes sense with the output object.
   *
   * That means that the type of filter will define what type of
   * object can be used as output. The filter function itself will not
   * touch the output object, but simply forward it to the operator
   * function.
   *
   * The operator function returns an int that is meant to indicate
   * how much output was produced. The filter function will accumulate
   * those values and return the sum.
   *
   * The filter is not required to produce a constant number of
   * outputs for each input. The function can be produce many outputs
   * or even none at all during the processing of each element.
   *
   * The value type for input and output is not required to be the
   * same. The input type is resolved by the value_type member type of
   * the input iterator type.
   *
   * \tparam InputIteratorType the type of the input iterator
   * \tparam OutputType the type of the output iterator
   * \tparam Functor the callback function type called for each element
   *
   * \param input_from starting position for the input iterator
   * \param input_to end position for the input iterator
   * \param output output container sent to the operator function
   * \param operation function that takes the element, the output
   * container and returns the number of outputted elements
   */
  template <typename InputIteratorType, typename OutputType,
            typename Functor >
  inline int
  filter(InputIteratorType input_from, InputIteratorType input_to,
         OutputType& output, Functor operation) {
    int counter = 0;
    while (input_from != input_to) {
      counter += operation(*input_from, output);
      input_from++;
    }
    return counter;
  }

}

#endif
