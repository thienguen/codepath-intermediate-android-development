package com.example.myapplication

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView

class BookAdapter (private val books: List<Book>) : RecyclerView.Adapter<BookAdapter.ViewHolder>()
{
    // Provide a direct reference to each of the views within a data item
    // Used to cache the views within the item layout for fast access
    inner class ViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
        // Your holder should contain and initialize a member variable
        // for any view that will be set as you render a row
        val authorTextView: TextView = itemView.findViewById<TextView>(R.id.author)
        val titleTextView: TextView = itemView.findViewById<TextView>(R.id.title)
    }

    // ... constructor and member variables
    // Usually involves inflating a layout from XML and returning the holder
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): BookAdapter.ViewHolder {
        val context = parent.context
        val inflater = LayoutInflater.from(context)
        // Inflate the custom layout
        val contactView = inflater.inflate(R.layout.book_item, parent, false)
        // Return a new holder instance
        return ViewHolder(contactView)
    }

    // Involves populating data into the item through holder
    override fun onBindViewHolder(viewHolder: BookAdapter.ViewHolder, position: Int) {
        // Get the data model based on position
        val book: Book = books[position]
//      Set item views based on your views and data model
//        val title = viewHolder.titleTextView
//        val author = viewHolder.authorTextView
//
//        title.text = book.title
//        author.text = book.author

        viewHolder.authorTextView.text = book.author
        viewHolder.titleTextView.text = book.title

    }

    // Returns the total count of items in the list
    override fun getItemCount(): Int {
        return books.size
    }
}