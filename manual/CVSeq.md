---
title: "CV-Seq Manual"
author: [SV Modular]
date: "October, 2019"
subject: "Charred Desert"
keywords: [CharredDesert, VCVRack, Manual]
lang: "en"
titlepage: true
logo: "images/SVModular.png"
...

# CV-SEQ

![CV-Seq Image](images/CVSeq.png "CV-Seq")

**CV-SEQ** is a four-step sequencer built for CV output.  Unlike note-based
sequencers, which output in the range of `-5`, *CV-SEQ* operates on CV standards,
outputting `0` through `10`.  This is helpful in automating CV tasks, allowing
for precision steps driven by a clock.  *CV-SEQ* outputs whatever value is set
by the combination of CV and knob for the duration of the _beat_.  If any of
these values change, the output will change as well.

**CV-SEQ** has 5 inputs and 1 output.  The primary input is the `CLK`, or clock;
this provides the step time, or _beat_ that triggers changing which value to
output.  The `CLK` triggers on a value of `1.7`.

`OUT` outputs the current step value.

Each step is controlled by a pair consisting of a CV input and a knob, representing
the values of `0` to `10`.  When the CV input is in use, its input is added to
value represented by the knob.  Thus, if the CV input is receiving `3.4`, and
the knob is set to `2.1`, the output will be `3.4`, the value of the input and
of the knob together.

Each triggered value will output its value for the duration of the _beat_, and
the LED will light up for each trigger position.
