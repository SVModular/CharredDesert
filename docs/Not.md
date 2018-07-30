# NOT

**NOT** provides inversion functionality, either as a waveform or as CV.

![NOT](images/not.png "NOT")

**NOT** has one `IN` input, and a single `OUT` output, as well as a type
selection.  Types vary the functionality of the module: _CV_ offers a binary
(on/off) output.  When the input is `1.7` or above, `1.7` is output, otherwise
`0` is output.  When _V/OCT_ is selected, the inverse is output; an input of `3.4`
outputs `-3.4`, and an input of `-1.8` outputs `1.8`.
