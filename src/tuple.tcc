#ifndef SIMPLE_REPL_TUPLE_TCC_
#define SIMPLE_REPL_TUPLE_TCC_

/**
 * @file tuple.tcc
 *
 * @a Tuple and @a Object definitions and manipulation functions.
 */

#define VMEMB_T class C, class P, class... FArgs
#define VMEMB Tuple<C*, void (P::*)(FArgs...)>

#define TMEMB_T class C, class R, class P, class... FArgs
#define TMEMB Tuple<C*, R (P::*)(FArgs...)>

/**
 * Empty tuple.
 *
 * @private
 */
template <class... Args>
struct Tuple {};

/**
 * Nested tuple.
 */
template <class H, class... Tail>
struct Tuple<H, Tail...> {
  H head;              ///< First element.
  Tuple<Tail...> tail; ///< Remaining elements.
};


/**
 * Make a nested tuple from a list of parameters.
 *
 * @param args Values to store in a nested tuple.
 *
 * @return Nested tuple containing @a args.
 */
template <class... Args>
Tuple<Args...> pack(Args... args) {
  Tuple<Args...> t = {args...};

  return t;
}

#endif
