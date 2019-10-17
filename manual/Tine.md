---
title: "Tine Manual"
author: [SV Modular]
date: "October, 2019"
subject: "Charred Desert"
keywords: [CharredDesert, VCVRack, Manual]
lang: "en"
titlepage: true
logo: "images/SVModular.png"
...

# Tine

![Tine Image](images/Tine.png "Tine")

**TINE** takes a signal and a `MOD` or Modulator (or Carrier) and outputs two
signals.

The `POLARITY` switch changes between bipolar and unipolar for the signal input.

`SPLIT` determines the voltage level at which to split the signal.  When the
modulator voltage is below `SPLIT` value, the signal is routed to the `LOW`
output.  When the modulator voltage is greater or equal to the `SPLIT` voltage,
the `AUD` input is sent to the `HIGH` output.

There are attenuators for both the `HIGH` and `LOW` outputs as well.
