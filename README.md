#Fish
A simulator for a math question that bugged me for quite a while.
The question is this (slightly altered):

**T** trout and **K** catfish swim in a pond.
A party is thrown nearby, and the fish are consumed until only one species is alive in the pond.
One of the fish is named Dan. What is the probability that Dan will die?

_Before_ I figured out the logical solution, I started working on this to check the answer via brute force.
Though after I found the solution, I was still working on this for experience...
(That's about the main thing I've been doing on GitHub.)
The `fish` and `simData` are the base classes that run the brute force simulation.

###Logical Solution
A note:
One of the first things I noticed when I was programming this project, was there are three kinds of fish.
(The types are listed below.)
This was the key to obtaining the solution.

This situation can end in only one of two ways:

- Dan dies.
- Dan does not die.

This can be refined to:

- Dan dies.
- All trout die.

Only Dan and trout are mentioned.
Notice that catfish aren't mentioned as an ending condition.
This leads to three kinds of fish:

- Dan
- Unnamed trout
- Unnamed catfish

So we don't care about catfish.
Dan is only one fish, and if we only look at Dan and trout, he only has a **1/(T+1)** chance of being picked.
That chance is the answer.
