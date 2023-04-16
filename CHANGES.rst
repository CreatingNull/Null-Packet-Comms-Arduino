Version 0.2.3
-------------

:Date: TBC

* Googletest framework updated to 1.13.0
* Correcting incorrect syntax used for rst external hyperlink in docs.
* Adding a check on CI build against the ``simple_example`` sketch to verify integration.

Version 0.2.2
-------------

:Date: 31-December-2022

* Fixing doc shields which inspected github workflows (see: `issue <https://github.com/badges/shields/issues/8671>`_).
* Defining test data as constant where it is used as a constant.

Version 0.2.1
-------------

:Date: 2-October-2022

* Used ``Serial.available`` calls in preference to the nested ``NullPacketComms.available`` internally.
* Sourcing doc metadata from ``library.properties``.
  This fixes a issues from me forgetting to maintain ``conf.py``.

Version 0.2.0
-------------

:Date: 2-October-2022

* Adding support for higher baud-rates 128000 to 2000000.
* Googletest framework updated to 1.12.1.
* Added ``waitOnAvailable`` private function to allow for dynamic delays pending next bytes.
* Reduced idle time from 25ms to 1ms while waiting on buffer to accumulate.
  This improves responsiveness, especially at higher baud rates.
* Error case for loss of start packet sync set to dynamically delay rather than blindly delay.

Version 0.1.2
-------------

:Date: 18-April-2022

* Explicit casting used on ``Serial.write`` calls to add support for platform cores with ambiguous prototypes.
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
