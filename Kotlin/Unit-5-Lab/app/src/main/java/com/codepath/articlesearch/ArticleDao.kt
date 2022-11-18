package com.codepath.articlesearch

import androidx.room.Dao
import androidx.room.Insert
import androidx.room.Query
import kotlinx.coroutines.flow.Flow


@Dao
interface  ArticleDao
{
//    creates an asynchronous data stream that sequentially emits values and completes normally or with an exception.
//    We can use getAll() function to listen to any database changes and update our UI!
//    This is way easier than [checking for new data ||---> (Flow allow us to we short cut the bracket)
//    ourselves or adding function calls to lifecycle changes or network calls].

    @Query("SELECT * FROM article_table")
    fun getAll() : Flow<List<ArticleEntity>>

    @Insert
    fun insertAll(articles : List<ArticleEntity> )

    @Insert
    fun insert(article : ArticleEntity)

    @Query("DELETE FROM article_table")
    fun deleteAll()
}