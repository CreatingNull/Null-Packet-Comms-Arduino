Version 0.2.0
-------------

:Date: 2-October-2022

* Adding support for higher baud-rates 128000 to 2000000.
* Googletest framework updated to 1.12.1.
* Added waitOnAvailable private function to allow for dynamic delays pending next bytes.
* Reduced idle time from 25ms to 1ms while waiting on buffer to accumulate.
  This improves responsiveness, especially at higher baud rates.
* Error case for loss of start packet sync set to dynamically delay rather than blindly delay.

Version 0.1.2
-------------

:Date: 18-April-2022

* Explicit casting used on Serial.write calls to add support for platform cores with ambiguous prototypes.
* Improvements to distributed docs.

Version 0.1.1
-------------

:Date: 14-February-2022

* Removing inclusion of files not required for the dist.
* Fixing permalinks to docs.

Version 0.1.0
-------------

:Date: 12-February-2022

* Initial release of the redesigned API.
