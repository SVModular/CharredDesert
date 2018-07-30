# CARBON

**CARBON** is a filter made to emulate a Moog resonance filter.  It has frequency
and resonance inputs also controllable by CV.

![CARBON Image](images/carbon.png "CARBON")

**CARBON** has 3 inputs and 1 output.  The primary input is `IN`, which provides
audio to be filtered.

`OUT` outputs filtered value.

A frequency is chosen by knob and CV input.  Knob values range from `20hz` to `7000hz`,
whereas CV inputs will multiply by `1000` (against `0` to `10` values).  These are added
together and clamped to `0` minimum, and `7000` maximum.

Resonance is controlled by the `REZ` parameter and CV input.  The knob provides
values between `0` and `4`, and the CV input scales by dividing by `10`.  These
are added for the final value, ranging from `0` to `4`.
