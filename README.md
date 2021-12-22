# Covid-Data-Analysis

Coded in C++.

The 2019–20 coronavirus pandemic is an ongoing pandemic of coronavirus disease 2019 (COVID-
19) caused by severe acute respiratory syndrome coronavirus 2 (SARS-CoV-2). As of 13 April
2020, more than 1.84 million cases of COVID-19 have been reported in 210 countries and territories,
resulting in more than 114,000 deaths. More than 421,000 people have recovered, although there
may be a possibility of reinfection.

In this project, you are required to answer queries regarding the COVID-19 pandemic. You are
provided with data regarding the pandemic containing information regarding the daily new cases
and cumulative cases for each country.
Data: https://who.sprinklr.com

You must read the given dataset and answer the following queries. For each query, think very
carefully about your approach in regards to both the time and space complexity of your solution.

1) On a given day, find the top 20 countries with the most confirmed cases. (Efficiently)

2) Find the country(s) with the highest new cases between two given dates. (Efficiently)

3) Find the starting and ending days of the longest spread period for a given country. The spread
period is defined as the period where daily new cases tend to increase. They may contain days
where new confirmed cases were relatively lower or none at all.
For example, [5, 2, 9, 16, 11, 27, 14, 45, 11] has a longest spread period elapsing 7 days from
day 2 (2) to day 8 (45). (Efficiently)

4) Find the longest daily death toll decrease period for a given country. They may contain days
where new confirmed deaths were relatively higher.
For example, [9, 5, 1, 16, 11, 23, 8, 3, 27, 14, 45, 11] has a longest daily death toll decrease
period of 4 {16, 11, 8, 3} (Efficiently)

5) You have decided to help with the relief effort by collaborating with an organization that
distributes essential supplies to affected regions. However, they must consider the overhead
cost for each country (distance, shipping etc.). They have assigned a score to each country,
which is simply the total number of active cases on the latest day (they prefer to help
countries with higher cases). A country may or may not be selected for aid. They have
gathered their projected costs for each country and have tasked you with finding the highest
possible score attainable as well as the countries selected given a budget of 300. (Efficiently)

6) We wish to compare the response of any two countries against this virus. To do this, we must
compare how similar the change of their daily active cases is. The similarity is measured by
the longest number of days their daily active cases share similar values. However, since it is
extremely unlikely that two countries have the exact same values for a sequence of days, we
define a compare threshold K such that any two countries are said to have ‘similar’ daily
active cases on a given day if their active cases differ <= K.
For example, C1 = [0, 0, 0, 1, 6, 10, 17, 27, 48, 94] & C2 = [3, 4, 8, 14, 31, 32, 49] and K = 10similarity (C1, C2) = 5 (C1[3:7] = C2[0:4])
Given two countries and the compare threshold K, find their similarity. (Efficiently)
