package com.example.datapersistence

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "event_table")
data class EventEntity (

    // They won't be nullable
    @ColumnInfo(name = "description") val description : String,
    @ColumnInfo(name = "date") val data : String,
    @PrimaryKey(autoGenerate = true) val id: Long = 0,
)
