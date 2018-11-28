# Project proposal

**Linear systems, signals and control (5LIU0) - Design Project**

**Topic: Time-delay angle-of-arrival estimation**

*Authors:*  
Benno Driessen (1399268 - b.p.a.driessen@student.tue.nl)  
Robert Paauw (1218883 - r.paauw@student.tue.nl)  

![raseone-soundwave-1](raseone-soundwave-1.png)

*Date: 20-11-2018*  
*Version 0.4*


<div style="page-break-after: always;"></div>

# Introduction
Time-delay angle-of-arrival estimation (TDAoA) is the technique of using two or multiple receivers to identify from which direction a particular signal is coming. For this project we will look at TDAoA for audio. The basic idea is that sound travels with a known speed (about 343m/s) and as a result it is possible to calculate distance from the time it takes to reach a certain location. If two microphones are placed at a known distance from each other then the angle can be calculated using the time difference between the audio arriving at microphone 1 and 2. This is shown in the figure below. It is suggested that this time difference can be extracted using cross-correlation on the signals from the microphones. Since signal processing is one of the main subjects of this course it will be the focus of this project. The project organization from the study guide will be used as guideline for this project.

![Setup schematic](Setup schematic.png)

## Example applications

Time-delay angle-of-arrival estimation on sound could potentially be used in a wide variety of domains. A few examples of applications where this technique might be interesting for:

- Conference calls - identify who speaks at a certain moment
- In home handfree video calls - aim the camera on the speaker and use beam-forming to improve sound quality
- Military - identify where the enemy is located based on sound
- Industrial - asset tracking in a factory or wharehouse using a "chirp"
- Marketing/analytics - Tracking costumers across a store to investigate patterns and improve the store's layout (there might be privacy concerns with this)

# Definitions

In the following paragraphs a few terms will be uses that need further clarification and/or definition.

## Accuracy

The *accuracy* if the measurement describes how large the error is between the estimated value and the real value. For TDAoA it is defined here as error in angle (in degrees) between these values.
$$
\begin{align*}
Error = θ_{measured} - θ_{actual}
\end{align*}
$$
The accuracy consists of two parts. One is the *static error* which is the difference between the average value of N measurements and the actual value. The second part is the *deviation* which is the difference between the highest and lowest value of these N measurements. An example is given below. If the actual value is 44,7 degrees then the *static error* is (45,0 - 44,7 = ) 0,3 degrees. The deviation is then (45,2 - 44,8 =) 0,4 degrees.

![Accuracy static and variable](Accuracy static and variable.png)

## Noise

For this project two types of noise are considered. One is *acoustic noise* and the other is *electronic noise*. Acoustic noise is audible noise produced from one or more audio sources that are not the main audio source which has to be estimated.  For example lets say TDAoA is used to track which person is speaking in a conference call on a hot day. In the background there is an AC unit blowing to cool down the room. The sound of the AC unit eventually reaches both microphones and therefore interfere with the algorithm.

The other type of noise is electronic noise (mostly white noise) which is produced by the microphone and amplifier. This is *random noise* which is different for both microphone channels. Electronic noise is hard to modify in the real world and therefore this will only be considered in the theory and simulations.

<div style="page-break-after: always;"></div>

# Project goals

The main goal of this project is to get some experience with research on and implementation of a digital signal processing algorithms. This goal can be achieved by answering the research questions below.

## Primary question

The primary research question that will be answered at the end of the project is:
"*What are the characteristics of TDAoA estimation based on the cross-correlation algorithm?*"

## Secondary questions involve:

These secondary questions help answering the primary question. These questions will be answered with theory, simulation and real-world testing where possible.

1. "How accurate can TDAoA be (in degrees) using this technique?"
1. "What is the relationship of the distance between the microphones and the accuracy?"
1. "How sensitive is this technique to noise?"
1. "What happens to the accuracy if the distance or angle of the sound source is increased?"
1. "How much processing time (in µS) does TDAoA using cross-correlation use per run for a given number of samples?"
1. "How does the sample resolution and sample rate affect the accuracy?"
1. "What is the minimum number of samples that have to be processed for using the cross-correlation algorithm?"

## Questions that are *outside* the scope of this project:

The following questions are interesting but will not contribute much to this project but are mentioned for completeness. They might be answered in a different project.

- "Is it possible to estimate the distance to the object with this method and a third microphone?"
- "Is it possible to estimate both *polar angle* and *azimuth angle* using this method a third microphone?"
- "Is it possible to distinguish between two or more audio sources using this method?"

<div style="page-break-after: always;"></div>

# Measurement and verification

*Zie questions voor nummers*

Signals to test with:

- Short beeps
- Chirp
- Pre-recorded audio



1. Meetopstelling voor nauwkeurigheid
   1. Apparaat op gradenboog -> met lat/laser de positie van luidspreker bepalen
      1. Statisch gedrag -> laten staan en kijken hoeveel de gemiddelde afwijking is
      2. Variatie -> laten staan en meten tussen welke waarden hij schommelt
2. Microfoons verplaatsen en meting 1 herhalen
3. Ruis
   1. Audiobron in de kamer zetten
   2. Ruis op microfoons vergelijken met simulatie -> geen externe ruis toevoegen
4. Range
   1. Increase distance and see what this does to the accuracy
   2. Increase angle and see what happens to the accuracy
5. Measure using internal timer or setting a pin when done and use a scope to measure the frequency/time
6. Testen met meerdere instellingen voor samplerate en resolutie
7. Mostly from theory. Test with number of samples below and above the minimum number.

<div style="page-break-after: always;"></div>

# Demo setup

For the demo the system will use two microphones to capture the sound. This will then be digitized and processed by a microcontroller (such as the STM32F407). During phase 2 "literature research and analytical investigation" the embedded platform will be selected. The demo setup is only used to evaluate the properties of the algorithm in a real world scenario and is *not* intended to be optimized for lowest cost or optimal performance.


# Challenges

These research questions create a few challenges to overcome. These are:

1. Find and study literature about TDAoA and cross-correlation in order to answer the theoretical part of the research questions. 
2. Develop models and simulations to test the theory and evaluate the the algorithm.
3. Implement the algorithm on the hardware along with the drivers for reading the ADC, timers and displaying the estimated angle.
4. Real world testing and analysis using the demo setup

# Deliverables

The deliverables are mostly defined by the *study guide* and are listed below for completeness.

- This project proposal document
- The final report
- Matlab simulation files
- Source code and hardware *schematics* for the demo setup
