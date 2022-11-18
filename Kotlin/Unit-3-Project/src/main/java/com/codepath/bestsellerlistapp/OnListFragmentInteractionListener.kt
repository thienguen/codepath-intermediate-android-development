package com.codepath.bestsellerlistapp

/**
 * This interface is used by the [BestMovieRecyclerViewAdapter] to ensure
 * it has an appropriate Listener.
 *
 */
interface OnListFragmentInteractionListener {
    fun onItemClick(item: BestMovie)
}
