# DTMF

**DTMF** plays dual tone multi-frequency sounds, the tones you hear when you
press the buttons on a phone.

![DTMF Image](images/dtmf.png "DTMF")

**DTMF** has 2 inputs: `GATE` and `V/OCT`, and a single `OUT`.

`GATE` is a CV input that acts as an ON/OFF switch for the tones.  When the `GATE`
receives a value of at least `1.7`, it starts playing whichever tone is specified
via the `V/OCT` input.

There are 16 tones to choose from, each with a different note in octaves 4 and 5:

|Note|Tone|Note|Tone|Note|Tone|Note|Tone|
|----|----|----|----|----|----|----|----|
|C-4 | 1  |C#-4| 2  |D-4 | 3  |D#-4| A  |
|E-4 | 4  |F-4 | 5  |F#-4| 5  |G-4 | B  |
|G#-4| 7  |A-4 | 8  |A#-4| 9  |B-4 | C  |
|C-5 | *  |C#-5| 0  |D-5 | #  |D#-5| D  |
