# Project proposal

**Linear systems, signals and control (5LIU0) - Design Project**

**Topic: Time-delay angle-of-arrival estimation**

*Authors:*  
Benno Driessen (1399268 - b.p.a.driessen@student.tue.nl)  
Robert Paauw (1218883 - r.paauw@student.tue.nl)  

![raseone-soundwave-1](raseone-soundwave-1.png)

*Date: 20-11-2018*  
*Version 0.2*


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

# Project goals

The main goal of this project is to get some experience with research on and implementation of a digital signal processing algorithms. This goal can be achieved by answering the research questions below.

## Primary question

The primary research question that will be answered at the end of the project is:
*"Is cross-correlation a viable way to estimate from which direction the sound is originating?"*

## Secondary questions involve:

These secondary questions help answering the primary question. These questions will be answered with theory, simulation and real-world testing where possible.

1. "How accurate can TDAoA be (in degrees) using this technique?"
   1. Static accuracy
   1. Variation
1. "What is the relationship of the distance between the microphones and the accuracy?"
1. "How sensitive is this technique to noise?"
   1. Ruis -> enkele bron
   1. Ruis -> ruis op microfoon (dit alleen simuleren)
1. "What is the range in both distance and angle of this system?"
   1. What happens to the accuracy?
1. "How much processing time does TDAoA using cross-correlation use per run?"
   1. With different sample rates
1. "How does the sample resolution and sample rate affect the result?"
1. "What is the minimum number of samples that have to be stored for cross-correlation?

## Questions that are *outside* the scope of this project:

The following questions are interesting but will not contribute much to this project but are mentioned for completeness. They might be answered in a different project.

- "Is it possible to estimate the distance to the object with this method and a third microphone?"
- "Is it possible to estimate both *polar angle* and *azimuth angle* using this method a third microphone?"
- "Is it possible to distinguish between two or more audio sources using this method?"

# Measurement and verification

*Zie questions voor nummers*

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

# Demo setup

For the demo the system will use two microphones to capture the sound. This will then be digitized and processed by a microcontroller (such as the STM32F407). During phase 2 "literature research and analytical investigation" the embedded platform will be selected. The demo setup is only used to evaluate the properties of the algorithm in a real world scenario and is *not* intended to be optimized for lowest cost or optimal performance.


# Challenges

These research questions create a few challenges to overcome. These are:

1. The first challenge would be to find and study literature about TDAoA and cross-correlation in order to answer the theoretical part of the research questions. 
2. During this time it will also be necessary to create models and simulations to test the theory and evaluate the the algorithm.
3. After that most hardware requirements can be estimated and the hardware can be chosen.
4. Then the algorithm has to be implemented on the hardware along with the drivers for reading the ADC, timers and displaying the estimated angle.
5. To reliably test the implementation against the theory and the models/simulations a test procedure has to be developed.



# Deliverables

The deliverables are mostly defined by the *study guide* and are listed below for completeness.

- This project proposal document
- The final report
- Source code of the model and algorithm
- Source code and hardware *schematics* for the demo setup
