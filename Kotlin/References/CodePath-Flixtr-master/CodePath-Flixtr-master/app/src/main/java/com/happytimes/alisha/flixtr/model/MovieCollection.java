package com.happytimes.alisha.flixtr.model;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import com.fasterxml.jackson.annotation.JsonInclude;
import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.annotation.JsonPropertyOrder;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by alishaalam on 7/19/16.
 */
@JsonInclude(JsonInclude.Include.NON_NULL)
@JsonPropertyOrder({
        "page",
        "results"
})
@JsonIgnoreProperties(ignoreUnknown=true)
public class MovieCollection {


    @JsonProperty("page")
    private long page;
    @JsonProperty("results")
    private List<Movie> movies = new ArrayList<Movie>();

    public MovieCollection() {
    }

    public MovieCollection(long page, List<Movie> movies) {
        this.page = page;
        this.movies = movies;
    }

    public long getPage() {
        return page;
    }

    public void setPage(long page) {
        this.page = page;
    }

    public List<Movie> getResults() {
        return movies;
    }

    public void setResults(List<Movie> movies) {
        this.movies = movies;
    }
}
