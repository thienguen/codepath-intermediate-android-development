package com.example.project6bitfitpart2

import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView

class BitFitAdapter(private val items: MutableList<BitFitItem>) : RecyclerView.Adapter<BitFitAdapter.ViewHolder>() {
    class ViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
        private val itemNameTv : TextView
        private val caloriesTv : TextView

        init {
            itemNameTv = itemView.findViewById(R.id.ItemNameTextView)
            caloriesTv = itemView.findViewById(R.id.CaloriesNumberTextView)
        }

        fun bind(item: BitFitItem) {
            itemNameTv.text = item.itemName
            caloriesTv.text = item.calories
        }
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val context = parent.context
        val inflater = LayoutInflater.from(context)
        val contactView = inflater.inflate(R.layout.entry_item, parent, false)
        return ViewHolder(contactView)
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val item = items[position]
        holder.bind(item)
    }

    override fun getItemCount(): Int {
        return items.size
    }
}