# Aakozi

Compute the "boomerang" statistics for each measured location using Ordinary Kriging and a simple linear variogram model.

We develop a pragmatic algorithm to automatically identify potential outliers in spatial data using a simple geostatistical framework. At each observation location, we temporarily remove the observation from the data set. With this reduced data set we interpolate the value at the observation location using Ordinary Kriging. We compare the interpolated value with the observed value. If the interpolated value and the observed value are significantly different, the observation is flagged as a potential outlier.

# Origin of the Project Name

The project name __Aakozi__ is the Ojibwe word for the animate intransitive verb "s/he is sick". See [http://ojibwe.lib.umn.edu](http://ojibwe.lib.umn.edu/search?utf8=%E2%9C%93&q=aakozi&commit=Search&type=ojibwe). This name seems appropriate for a program used to identify potental outliers.

