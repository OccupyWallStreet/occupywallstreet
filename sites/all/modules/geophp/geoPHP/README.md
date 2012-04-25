GeoPHP is a open-source native PHP library for doing geometry operations. It is written entirely in PHP and 
can therefore run on shared hosts. It can read and write a wide variety of formats (WKT, WKB, GeoJSON, 
KML, GPX, GeoRSS). It works with all Simple-Feature geometries (Point, LineString, Polygon, GeometryCollection etc.)
and can be used to get centroids, bounding-boxes, area, and a wide variety of other useful information. 

geoPHP also helpfully wraps the GEOS php extension so that applications can get a transparent performance 
increase when GEOS is installed on the server. When GEOS is installed, geoPHP also becomes
fully compliant with the OpenGIS® Implementation Standard for Geographic information. With GEOS you get the 
full-set of openGIS functions in PHP like Union, IsWithin, Touches etc. This means that applications
get a useful "core-set" of geometry operations that work in all environments, and an "extended-set"of operations 
for environments that have GEOS installed. 

See the 'getting started' section below for references and examples of everything that geoPHP can do.

This project is currently looking for co-maintainers. If you think you can help out, please send me a 
message. Forks are also welcome, please issue pull requests and I will merge them into the main branch.

Getting Started
-----------------------

 * The lastest stable version can always be downloaded at: <https://github.com/downloads/phayes/geoPHP/geoPHP.tar.gz>
 * Read the API Reference at: <https://github.com/phayes/geoPHP/wiki/API-Reference>
 * Examples
   * Using geoPHP as a GIS format converter: <http://github.com/phayes/geoPHP/wiki/Example-format-converter>
 * Other Interesting Links:
   * Learn about GEOS integration at: <https://github.com/phayes/geoPHP/wiki/GEOS>

Example usage
-------------------------------------------------

```php
<?php
include_once('geoPHP.inc');

// Polygon WKT example
$polygon = geoPHP::load('POLYGON((1 1,5 1,5 5,1 5,1 1),(2 2,2 3,3 3,3 2,2 2))','wkt');
$area = $polygon->getArea();
$centroid = $polygon->getCentroid();
$centX = $centroid->getX();
$centY = $centroid->getY();

print "This polygon has an area of ".$area." and a centroid with X=".$centX." and Y=".$centY;

// MultiPoint json example
print "<br/>";
$json = 
'{
   "type": "MultiPoint",
   "coordinates": [
       [100.0, 0.0], [101.0, 1.0]
   ]
}';

$multipoint = geoPHP::load($json, 'json');
$multipoint_points = $multipoint->getComponents();
$first_wkt = $multipoint_points[0]->out('wkt');

print "This multipolygon has ".$multipoint->numGeometries()." points. The first point has a wkt representation of ".$first_wkt;
```

Credit
-------------------------------------------------

Maintainer: Patrick Hayes

Code From:

 * CIS by GeoMemes Research <http://www.geomemes.com>
 * gisconverter.php by Arnaud Renevier <https://github.com/arenevier/gisconverter.php>
 * Dave Tarc <https://github.com/dtarc>

This library is open-source and dual-licensed under both the Modified BSD License and GPLv2. Either license may be used at your option.           
