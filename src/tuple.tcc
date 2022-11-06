#pragma once

/*! Tuple.
 *
 * \tparam Membs... 
 */
template <class... Membs>
struct Tuple {};

using Empty = Tuple<>&;
using EmptyC = Tuple<> const&;

// Full definition.
template <class H, class... Tail>
struct Tuple<H, Tail...> {
  H head;               //< First element.
  Tuple<Tail...> tail;  //< Remaining elements.
};


inline void fill(Empty) {}

template <class H, class... Tail>
void fill(Tuple<H, Tail...>& t, H head, Tail... tail) {
  t.head = head;
  fill(t.tail, tail...);
}

/**
 * Make a tuple from a list of parameters.
 *
 * \param args Values to store in a tuple.
 *
 * \return Tuple containing `args`.
 */
template <class... Args>
Tuple<Args...> pack(Args... args) {
  Tuple<Args...> t;
  fill(t, args...);

  return t;
}

template <class... Args>
Tuple<Args...> param(Args... args) {
  return pack(args...);
}

template <class... Args>
Tuple<Args...> func(Args... args) {
  return pack(args...);
}
