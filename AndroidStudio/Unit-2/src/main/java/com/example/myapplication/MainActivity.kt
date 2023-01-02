package com.example.myapplication

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        // Lookup the recyclerview in activity layout
        val rvBooks = findViewById<RecyclerView>(R.id.rvBooks)

        // Initialize data
        val books = listOf<Book>(
            Book("The Great Gatsby", "F. Scott Fitzgerald", "1925"),
            Book("The Catcher in the Rye", "J. D. Salinger", "1951"),
            Book("To Kill a Mockingbird", "Harper Lee", "1960"),
            Book("Pride and Prejudice", "Jane Austen", "1813"),
            Book("The Lord of the Rings", "J. R. R. Tolkien", "1954"),
            Book("The Hobbit", "J. R. R. Tolkien", "1937"),
            Book("Harry Potter and the Sorcerer's Stone", "J. K. Rowling", "1997"),
            Book("The Hunger Games", "Suzanne Collins", "2008")
        )

        // Create adapter passing in the sample user data
        val adaptee = BookAdapter(books)

        // Attach the adapter to the recyclerview to populate items
        rvBooks.adapter = adaptee

        // Set layout manager to position the items
        rvBooks.layoutManager = LinearLayoutManager(this)

        // That's all!
    }
}