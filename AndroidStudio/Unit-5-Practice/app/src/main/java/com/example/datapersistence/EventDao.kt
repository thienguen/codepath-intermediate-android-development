package com.example.datapersistence

import androidx.room.Dao
import androidx.room.Insert
import androidx.room.Query
import kotlinx.coroutines.flow.Flow

@Dao
interface EventDao{
    @Query("SELECT * FROM event_table")
    fun getAll(): Flow<List<EventEntity>>

    @Insert
    fun insertAll(articles : List<EventEntity>)

    @Insert
    fun insert(event : EventEntity)

    @Query("DELETE FROM event_table")
    fun deleteAll()
}