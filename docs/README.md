# Charred Desert Manual

## DTMF

Plays DTMF (telephone) tones as notes on the scale, starting at Octave 5, C.

![DTMF](images/dtmf.png)

Plays the following tones:

```
1 2 3 A
4 5 6 B
7 8 9 C
* 0 # D
```

### Input

* CV - triggers at 1.7, determines whether the note should be played
* V/Oct - Chooses which of the 16 notes to play

### Output

* Out - waveform

## Noise

Generates white or pink noise.

![Noise](images/noise.png)

Switchable between white and pink noise.

### Input

* CV - triggers at 1.7, determines whether the note should be played
* Switch - switches between white and pink noise

### Output

* Out - waveform

## CVSeq

"Sequences" CV values with an input clock

![CVSeq](images/cvseq.png)

Allows for 4 steps.

### Input

* CV - triggers at 1.7, acts as the clock
* Knobs - a single knob for each step, with outputs between 0 and 10

### Output

* Out - CV values ranging from 0 to 10

## Not

Switchable Not module

![Not](images/not.png)

Outputs the opposite of the input.

### Input

* In - switchable input between logical (CV) and waveform
* Switch - switches modes between logical and waveform

### Output

* Out - outputs on/off (0 or 1.7) or inverted (-5 to 5) value of the input
