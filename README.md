# BingeHackers

IMDB Scrapper and Offline Database using Binary Tree Algorithms

**Team Name:** BingeHackers    
 
**Team Members:** Miguel Caputo, Juan Gonzalez, Nathan Whelden
 
# Problem: What problem are we trying to solve?

IMDb is an online database containing millions of entries on media, including information on tv series, movies, actors, reviews, and more.  IMDb’s datasets are publicly available; however, they are unorganized and each contains over a million tuples of data. IMDb’s dataset on television series, short films, and movies alone contains over 1.5 million entries, presenting an issue for a user who wants to find information on a tv series.

# Motivation: Why is this a problem?

In the case that IDMb’s platform was down, a user would have to rely on the datasets for information.  Unfortunately, trying to manually check through each entry of a dataset to find a single tv series would take hours.  A user does not have the patience or time to manually search through this much data, so a program that can quickly search for the desired information in a few seconds would be a preferable alternative.

# Features: When do we know that we have solved the problem?

We would know that the stated problem is solved when the user is able to search for information about a desired television show without needing to use the IMDB website or any resource outside our program.

Our program will load tuples of data from IMDb’s dataset on television series, short films, and movies.  To narrow the scope of the project from over a million entries of data to under two hundred thousand, only entries related to television series will be used.  After the data has been loaded into a stream, the user will then be able to choose which data structure they want to store the entries into.  Each entry will be stored as an object, with object members containing information such as name, runtime, and genre.  The user will then be prompted to search for a television series by providing a title.  If the series is found, the information from the respective dataset entry will be displayed.

# Data

Public data set we will be using and the link to the public data set) or (Schema of randomly generated data - i.e. what are the different columns in our dataset and the respective data types) 

For the project, we would use a publicly available .tsv file containing all the relevant information for tv series, movies, and shorts that the IMDB website uses. The information contained in the data set by different columns is:

- **tconst**: A combination of characters that when included at the end of https://www.imdb.com/title/ can give us easy access to the IMDB webpage of the series.
- **titleType**: A string that can be either, short, movie, video, tvEpisode, tvSeries, tvMovie or tvMiniSeries.
- **primaryTitle**: A string containing the name of the show.
- **originalTitle**: If the show name was translated from its original language, this column includes the original name.
- **isAdult**: A boolean expression containing a 0 if the show is not adult-rated or a 1 if it is.
- **starterYear**: An int containing the year when the show was started.
- **endYear**: An int containing the year when the show ended if available.
- **runtimeMinutes**: An int containing the length of each episode or the full length of each show.
- **genres**: An string containing all the genres of the show, each one separated by a “,”

For the data set, each column is separated by tabs and for any show that there is no information available for in one of these columns, the data set would have an “\N”. 
This data set contains almost 1.6 million shows, so for the purpose of this project, it would be reduced to just non-adult “tvSeries” after 1990, and also we would erase all titles without a complete relevant data set. In addition, we are thinking of maybe adding another column that would contain the rating for each show, but we are not sure yet.

# Tools: Programming languages or any tools/frameworks we will be using.

For this project, we will be using Python and C++. We plan on using Python code to trim the data set. We plan on using C++ for the rest of the project, such as the implementation of the data structures, algorithms, functions, and the user menu.

# References

https://datasets.imdbws.com/
