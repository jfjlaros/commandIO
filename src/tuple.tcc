#ifndef USERIO_TUPLE_TCC_
#define USERIO_TUPLE_TCC_

#define VMEMB_T class C, class P, class... FArgs
#define VMEMB Tuple<C*, void (P::*)(FArgs...)>

#define TMEMB_T class C, class R, class P, class... FArgs
#define TMEMB Tuple<C*, R (P::*)(FArgs...)>

/**
 * Tuple.
 *
 * \struct Tuple
 */
template <class... Args>
struct Tuple {};

// Full definition.
template <class H, class... Tail>
struct Tuple<H, Tail...> {
  H head;              ///< First element.
  Tuple<Tail...> tail; ///< Remaining elements.
};


/**
 * Make a tuple from a list of parameters.
 *
 * \param args Values to store in a tuple.
 *
 * \return Tuple containing `args`.
 */
template <class... Args>
Tuple<Args...> pack(Args... args) {
  Tuple<Args...> t = {args...};

  return t;
}

#endif
