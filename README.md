
# Setup Instructions for HandSystemP2 Project

This document provides a simple and clear guide to help you set up and run the HandSystemP2 project, which involves hand tracking and sound/particle generation.

## Prerequisites

Ensure the following tools are installed on your computer:
- Node.js (https://nodejs.org/en/download/)
- An IDE that supports C++ (e.g., Visual Studio or Xcode)

## Steps to Setup and Run

### 1. Clone the Repositories

First, clone both required repositories to your local machine using the following commands:

Command Line:
You might need to clone this inside "\of_v0.12.0_vs_release\apps\myApps" then import via project generator app:
git clone https://github.com/Mohd6288/HandSystemP2
git clone https://github.com/monlim/MediaPipe-Hands-OSC

### 2. Install Node.js Packages

Navigate to the MediaPipe-Hands-OSC directory and install the necessary packages:

Command Line:
cd MediaPipe-Hands-OSC
npm install

### 3. Run the OSC Bridge

Start the OSC bridge to facilitate communication between the hand tracking webpage and your local project:

Command Line:
node bridge.js

### 4. Open the Hand Tracking Webpage

Open the following URL in your web browser to begin hand tracking:

https://monlim.github.io/MediaPipe-Hands-OSC/

### 5. Build and Run HandSystemP2

Open the HandSystemP2 project in your IDE, build it, and run the executable. Use a dual-monitor setup for optimal experience:
- One screen for the MediaPipe-Hands-OSC tracking webpage.
- One screen for the HandSystemP2 application.

## Running the Application

With both the webpage and the HandSystemP2 application running, move your hands in front of your webcam. The application should respond with sound and visual particle effects based on your hand movements.

## Troubleshooting

If you encounter issues, ensure all paths and dependencies are correctly configured in your IDE, and that all Node.js packages are installed without errors.

Thank you for following these instructions. Enjoy interacting with the HandSystemP2 project!
