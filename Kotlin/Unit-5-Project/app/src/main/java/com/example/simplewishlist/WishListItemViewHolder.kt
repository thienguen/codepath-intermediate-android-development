package com.example.simplewishlist

import android.content.Context
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.example.simplewishlist.databinding.WishlistItemsBinding


// Class View Holder in Adapter now created separately
// I compared them as how files are linked, as it seem like -- they don't

class WishListItemViewHolder(
    private val context: Context,
    private val binding: WishlistItemsBinding
): RecyclerView.ViewHolder(binding.root)
{
    val nameTextView : TextView = binding.nameItem
    val caloriesTextView : TextView = binding.caloriesItem
    val timeTextView : TextView = binding.timeItem

    fun bindWishListItem(wish: WishListItem)
    {
        binding.nameItem.text = wish.name
        binding.caloriesItem.text = wish.calories.toString()
        binding.timeItem.text = wish.time
    }
}
