package com.happytimes.alisha.flixtr.model;

import com.fasterxml.jackson.annotation.JsonInclude;
import com.fasterxml.jackson.annotation.JsonProperty;
import com.fasterxml.jackson.annotation.JsonPropertyOrder;

import java.util.ArrayList;
import java.util.List;

/**
 * Created by alishaalam on 7/24/16.
 */

@JsonInclude(JsonInclude.Include.NON_NULL)
@JsonPropertyOrder({
        "id",
        "quicktime",
        "youtube"
})
public class TrailerCollection {
    @JsonProperty("id")
    private Integer id;
    @JsonProperty("quicktime")
    private List<Object> quicktime = new ArrayList<Object>();
    @JsonProperty("youtube")
    private List<MovieTrailer> movieTrailers = new ArrayList<MovieTrailer>();

    /**
     *
     * @return
     * The id
     */
    @JsonProperty("id")
    public Integer getId() {
        return id;
    }

    /**
     *
     * @param id
     * The id
     */
    @JsonProperty("id")
    public void setId(Integer id) {
        this.id = id;
    }

    /**
     *
     * @return
     * The quicktime
     */
    @JsonProperty("quicktime")
    public List<Object> getQuicktime() {
        return quicktime;
    }

    /**
     *
     * @param quicktime
     * The quicktime
     */
    @JsonProperty("quicktime")
    public void setQuicktime(List<Object> quicktime) {
        this.quicktime = quicktime;
    }

    /**
     *
     * @return
     * The youtube
     */
    @JsonProperty("youtube")
    public List<MovieTrailer> getMovieTrailers() {
        return movieTrailers;
    }

    /**
     *
     * @param youtube
     * The youtube
     */
    @JsonProperty("youtube")
    public void setMovieTrailers(List<MovieTrailer> youtube) {
        this.movieTrailers = youtube;
    }
}

