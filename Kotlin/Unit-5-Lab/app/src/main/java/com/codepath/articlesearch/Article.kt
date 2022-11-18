package com.codepath.articlesearch

import android.support.annotation.Keep
import kotlinx.serialization.SerialName
import kotlinx.serialization.Serializable


@Keep
@Serializable
data class SearchNewsResponse(
    @SerialName("response")
    val response: BaseResponse?
)

@Keep
@Serializable
data class BaseResponse(
    @SerialName("docs")
    val docs: List<Article>?
)

@Keep
@Serializable
data class Article(
    @SerialName("abstract")
    val abstract: String?,
    @SerialName("byline")
    val byline: Byline?,
    @SerialName("headline")
    val headline: HeadLine?,
    @SerialName("multimedia")
    val multimedia: List<MultiMedia>?,
) : java.io.Serializable {
    val mediaImageUrl = "https://www.nytimes.com/${multimedia?.firstOrNull { it.url != null }?.url ?: ""}"
}

// This will use the first media in the array,
// if it's available (by checking using firstOrNull),
// and parse through the MultiMedia to get the url for the image.
// If it is not available, it will set an empty string for the mediaImageUrl.

@Keep
@Serializable
data class HeadLine(
    @SerialName("main")
    val main: String
) : java.io.Serializable


@Keep
@Serializable
data class Byline(
    @SerialName("original")
    val original : String? = null
) : java.io.Serializable


@Keep
@Serializable
data class MultiMedia(
    @SerialName("url")
    val url: String?
) : java.io.Serializable
