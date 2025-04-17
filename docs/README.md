```mermaid
<svg viewBox="0 0 800 600" xmlns="http://www.w3.org/2000/svg">
  <!-- Background and title -->
  <rect width="800" height="600" fill="#f8f9fa" />
  <text x="400" y="30" text-anchor="middle" font-family="Arial" font-size="20" font-weight="bold">Thermoelectric Temperature Control - System Architecture</text>
  
  <!-- Master Processor (Main Controller) -->
  <rect x="300" y="80" width="200" height="100" fill="#d1e7dd" stroke="#198754" stroke-width="2" rx="5" />
  <text x="400" y="110" text-anchor="middle" font-family="Arial" font-size="16" font-weight="bold">Master Processor</text>
  <text x="400" y="135" text-anchor="middle" font-family="Arial" font-size="12">- Mode Selection</text>
  <text x="400" y="155" text-anchor="middle" font-family="Arial" font-size="12">- Peltier Control</text>
  <text x="400" y="175" text-anchor="middle" font-family="Arial" font-size="12">- Temperature Processing</text>
  
  <!-- Slave Processor 1 (LCD Controller) -->
  <rect x="100" y="250" width="180" height="80" fill="#cfe2ff" stroke="#0d6efd" stroke-width="2" rx="5" />
  <text x="190" y="280" text-anchor="middle" font-family="Arial" font-size="16" font-weight="bold">Slave Processor 1</text>
  <text x="190" y="305" text-anchor="middle" font-family="Arial" font-size="12">LCD Controller</text>
  
  <!-- Slave Processor 2 (LED Lightbar) -->
  <rect x="520" y="250" width="180" height="80" fill="#cfe2ff" stroke="#0d6efd" stroke-width="2" rx="5" />
  <text x="610" y="280" text-anchor="middle" font-family="Arial" font-size="16" font-weight="bold">Slave Processor 2</text>
  <text x="610" y="305" text-anchor="middle" font-family="Arial" font-size="12">LED Lightbar Controller</text>
  
  <!-- Input Devices -->
  <rect x="100" y="80" width="120" height="100" fill="#fff3cd" stroke="#ffc107" stroke-width="2" rx="5" />
  <text x="160" y="110" text-anchor="middle" font-family="Arial" font-size="16" font-weight="bold">Input Devices</text>
  <text x="160" y="135" text-anchor="middle" font-family="Arial" font-size="12">- Keypad</text>
  <text x="160" y="155" text-anchor="middle" font-family="Arial" font-size="12">- RTC (I2C)</text>
  <text x="160" y="175" text-anchor="middle" font-family="Arial" font-size="12">- Rotary Encoder (opt)</text>
  
  <!-- Temperature Sensors -->
  <rect x="580" y="80" width="120" height="100" fill="#f8d7da" stroke="#dc3545" stroke-width="2" rx="5" />
  <text x="640" y="110" text-anchor="middle" font-family="Arial" font-size="16" font-weight="bold">Sensors</text>
  <text x="640" y="135" text-anchor="middle" font-family="Arial" font-size="12">- LM19 (Ambient)</text>
  <text x="640" y="155" text-anchor="middle" font-family="Arial" font-size="12">- LM92 (Plant)</text>
  <text x="640" y="175" text-anchor="middle" font-family="Arial" font-size="12">I2C Temperature</text>
  
  <!-- Output Devices -->
  <rect x="300" y="400" width="200" height="100" fill="#d3d3d3" stroke="#6c757d" stroke-width="2" rx="5" />
  <text x="400" y="430" text-anchor="middle" font-family="Arial" font-size="16" font-weight="bold">Peltier Control</text>
  <text x="400" y="455" text-anchor="middle" font-family="Arial" font-size="12">- MOSFET Switching</text>
  <text x="400" y="475" text-anchor="middle" font-family="Arial" font-size="12">- Relay Control</text>
  <text x="400" y="495" text-anchor="middle" font-family="Arial" font-size="12">- 12V Power Management</text>
  
  <!-- LCD Display -->
  <rect x="100" y="400" width="180" height="100" fill="#e2e3e5" stroke="#6c757d" stroke-width="2" rx="5" />
  <text x="190" y="430" text-anchor="middle" font-family="Arial" font-size="16" font-weight="bold">LCD Display</text>
  <text x="190" y="455" text-anchor="middle" font-family="Arial" font-size="12">- Mode</text>
  <text x="190" y="475" text-anchor="middle" font-family="Arial" font-size="12">- Temperatures</text>
  <text x="190" y="495" text-anchor="middle" font-family="Arial" font-size="12">- Time in Mode</text>
  
  <!-- LED Lightbar -->
  <rect x="520" y="400" width="180" height="100" fill="#e2e3e5" stroke="#6c757d" stroke-width="2" rx="5" />
  <text x="610" y="430" text-anchor="middle" font-family="Arial" font-size="16" font-weight="bold">LED Lightbar</text>
  <text x="610" y="455" text-anchor="middle" font-family="Arial" font-size="12">- Heating Indicator</text>
  <text x="610" y="475" text-anchor="middle" font-family="Arial" font-size="12">- Cooling Indicator</text>
  <text x="610" y="495" text-anchor="middle" font-family="Arial" font-size="12">- Status Display</text>
  
  <!-- Connections -->
  <!-- Master to Slaves -->
  <line x1="400" y1="180" x2="400" y2="220" stroke="#000" stroke-width="2" stroke-dasharray="5,5" />
  <text x="410" y="210" font-family="Arial" font-size="12">I2C Bus</text>
  <line x1="400" y1="220" x2="190" y2="250" stroke="#000" stroke-width="2" stroke-dasharray="5,5" />
  <line x1="400" y1="220" x2="610" y2="250" stroke="#000" stroke-width="2" stroke-dasharray="5,5" />
  
  <!-- Inputs to Master -->
  <line x1="220" y1="130" x2="300" y2="130" stroke="#000" stroke-width="2" />
  <polygon points="295,125 305,130 295,135" fill="#000" />
  
  <!-- Sensors to Master -->
  <line x1="580" y1="130" x2="500" y2="130" stroke="#000" stroke-width="2" />
  <polygon points="505,125 495,130 505,135" fill="#000" />
  
  <!-- Master to Peltier -->
  <line x1="400" y1="180" x2="400" y2="400" stroke="#000" stroke-width="2" />
  <polygon points="395,395 400,405 405,395" fill="#000" />
  
  <!-- Slave 1 to LCD -->
  <line x1="190" y1="330" x2="190" y2="400" stroke="#000" stroke-width="2" />
  <polygon points="185,395 190,405 195,395" fill="#000" />
  
  <!-- Slave 2 to LED -->
  <line x1="610" y1="330" x2="610" y2="400" stroke="#000" stroke-width="2" />
  <polygon points="605,395 610,405 615,395" fill="#000" />
</svg>
```

```mermaid
<svg viewBox="0 0 800 900" xmlns="http://www.w3.org/2000/svg">
  <!-- Background and title -->
  <rect width="800" height="900" fill="#f8f9fa" />
  <text x="400" y="30" text-anchor="middle" font-family="Arial" font-size="20" font-weight="bold">Thermoelectric Temperature Control - Flow Chart</text>
  
  <!-- Start -->
  <ellipse cx="400" cy="70" rx="80" ry="30" fill="#d1e7dd" stroke="#198754" stroke-width="2" />
  <text x="400" y="75" text-anchor="middle" font-family="Arial" font-size="14">Start</text>
  
  <!-- Initialize System -->
  <rect x="300" y="120" width="200" height="50" fill="#cfe2ff" stroke="#0d6efd" stroke-width="2" rx="5" />
  <text x="400" y="150" text-anchor="middle" font-family="Arial" font-size="14">Initialize System</text>
  
  <!-- Read Keypad Input -->
  <rect x="300" y="200" width="200" height="50" fill="#fff3cd" stroke="#ffc107" stroke-width="2" rx="5" />
  <text x="400" y="230" text-anchor="middle" font-family="Arial" font-size="14">Read Keypad Input</text>
  
  <!-- Mode Selection Decision -->
  <polygon points="400,280 500,330 400,380 300,330" fill="#f8d7da" stroke="#dc3545" stroke-width="2" />
  <text x="400" y="325" text-anchor="middle" font-family="Arial" font-size="14">Mode Selection</text>
  <text x="400" y="345" text-anchor="middle" font-family="Arial" font-size="14">A/B/C/D?</text>
  
  <!-- A: Heat Mode -->
  <rect x="100" y="380" width="150" height="50" fill="#d1e7dd" stroke="#198754" stroke-width="2" rx="5" />
  <text x="175" y="410" text-anchor="middle" font-family="Arial" font-size="14">A: Heat Mode</text>
  
  <!-- B: Cool Mode -->
  <rect x="280" y="380" width="150" height="50" fill="#cfe2ff" stroke="#0d6efd" stroke-width="2" rx="5" />
  <text x="355" y="410" text-anchor="middle" font-family="Arial" font-size="14">B: Cool Mode</text>
  
  <!-- C: Match Mode -->
  <rect x="460" y="380" width="150" height="50" fill="#fff3cd" stroke="#ffc107" stroke-width="2" rx="5" />
  <text x="535" y="410" text-anchor="middle" font-family="Arial" font-size="14">C: Match Mode</text>
  
  <!-- D: Off Mode -->
  <rect x="640" y="380" width="150" height="50" fill="#e2e3e5" stroke="#6c757d" stroke-width="2" rx="5" />
  <text x="715" y="410" text-anchor="middle" font-family="Arial" font-size="14">D: Off Mode</text>
  
  <!-- Read Temperatures -->
  <rect x="300" y="460" width="200" height="50" fill="#cfe2ff" stroke="#0d6efd" stroke-width="2" rx="5" />
  <text x="400" y="490" text-anchor="middle" font-family="Arial" font-size="14">Read Temperatures</text>
  
  <!-- Calculate Moving Average -->
  <rect x="300" y="540" width="200" height="50" fill="#cfe2ff" stroke="#0d6efd" stroke-width="2" rx="5" />
  <text x="400" y="570" text-anchor="middle" font-family="Arial" font-size="14">Calculate Moving Average</text>
  
  <!-- Control Decision -->
  <polygon points="400,620 500,670 400,720 300,670" fill="#f8d7da" stroke="#dc3545" stroke-width="2" />
  <text x="400" y="660" text-anchor="middle" font-family="Arial" font-size="14">Control Decision</text>
  <text x="400" y="680" text-anchor="middle" font-family="Arial" font-size="14">Based on Mode</text>
  
  <!-- Activate Peltier Device -->
  <rect x="300" y="750" width="200" height="50" fill="#d1e7dd" stroke="#198754" stroke-width="2" rx="5" />
  <text x="400" y="780" text-anchor="middle" font-family="Arial" font-size="14">Activate Peltier Device</text>
  
  <!-- 5 min check -->
  <polygon points="400,830 500,870 400,910 300,870" fill="#f8d7da" stroke="#dc3545" stroke-width="2" />
  <text x="400" y="870" text-anchor="middle" font-family="Arial" font-size="14">5 min elapsed?</text>
  
  <!-- Connections -->
  <line x1="400" y1="100" x2="400" y2="120" stroke="#000" stroke-width="2" />
  <line x1="400" y1="170" x2="400" y2="200" stroke="#000" stroke-width="2" />
  <line x1="400" y1="250" x2="400" y2="280" stroke="#000" stroke-width="2" />
  
  <!-- Mode Selection Connections -->
  <line x1="300" y1="330" x2="175" y2="380" stroke="#000" stroke-width="2" />
  <text x="230" y="345" text-anchor="middle" font-family="Arial" font-size="12">A</text>
  
  <line x1="355" y1="330" x2="355" y2="380" stroke="#000" stroke-width="2" />
  <text x="365" y="355" text-anchor="middle" font-family="Arial" font-size="12">B</text>
  
  <line x1="445" y1="330" x2="535" y2="380" stroke="#000" stroke-width="2" />
  <text x="500" y="345" text-anchor="middle" font-family="Arial" font-size="12">C</text>
  
  <line x1="500" y1="330" x2="715" y2="380" stroke="#000" stroke-width="2" />
  <text x="600" y="345" text-anchor="middle" font-family="Arial" font-size="12">D</text>
  
  <!-- Joining Modes -->
  <line x1="175" y1="430" x2="175" y2="490" stroke="#000" stroke-width="2" />
  <line x1="355" y1="430" x2="355" y2="490" stroke="#000" stroke-width="2" />
  <line x1="535" y1="430" x2="535" y2="490" stroke="#000" stroke-width="2" />
  <line x1="715" y1="430" x2="715" y2="490" stroke="#000" stroke-width="2" />
  
  <line x1="175" y1="490" x2="300" y2="490" stroke="#000" stroke-width="2" />
  <line x1="535" y1="490" x2="500" y2="490" stroke="#000" stroke-width="2" />
  <line x1="715" y1="490" x2="590" y2="490" stroke="#000" stroke-width="2" stroke-dasharray="5,5" />
  <text x="650" y="480" text-anchor="middle" font-family="Arial" font-size="10">(Off Mode bypasses control)</text>
  
  <!-- Connect Read to Moving Average -->
  <line x1="400" y1="510" x2="400" y2="540" stroke="#000" stroke-width="2" />
  
  <!-- Connect Moving Average to Control Decision -->
  <line x1="400" y1="590" x2="400" y2="620" stroke="#000" stroke-width="2" />
  
  <!-- Connect Control Decision to Peltier Activation -->
  <line x1="400" y1="720" x2="400" y2="750" stroke="#000" stroke-width="2" />
  
  <!-- Connect Peltier to Time Check -->
  <line x1="400" y1="800" x2="400" y2="830" stroke="#000" stroke-width="2" />
  
  <!-- Time Check Loop -->
  <line x1="300" y1="870" x2="240" y2="870" stroke="#000" stroke-width="2" />
  <line x1="240" y1="870" x2="240" y2="230" stroke="#000" stroke-width="2" />
  <line x1="240" y1="230" x2="300" y2="230" stroke="#000" stroke-width="2" />
  <text x="270" y="850" text-anchor="middle" font-family="Arial" font-size="12">No</text>
  
  <!-- Time Check to Off Mode -->
  <line x1="500" y1="870" x2="760" y2="870" stroke="#000" stroke-width="2" />
  <line x1="760" y1="870" x2="760" y2="410" stroke="#000" stroke-width="2" />
  <line x1="760" y1="410" x2="790" y2="410" stroke="#000" stroke-width="2" />
  <text x="530" y="850" text-anchor="middle" font-family="Arial" font-size="12">Yes (Turn off after 5 min)</text>
  
  <!-- Extra Notes -->
  <text x="400" y="80" text-anchor="middle" font-family="Arial" font-size="10" fill="#6c757d">(Master processor controls main flow)</text>
  <text x="135" y="450" text-anchor="middle" font-family="Arial" font-size="10" fill="#6c757d">(Display on LED bar)</text>
  <text x="665" y="450" text-anchor="middle" font-family="Arial" font-size="10" fill="#6c757d">(Turn off MOSFET)</text>
  <text x="400" y="520" text-anchor="middle" font-family="Arial" font-size="10" fill="#6c757d">(Sample every 0.5s)</text>
  <text x="400" y="600" text-anchor="middle" font-family="Arial" font-size="10" fill="#6c757d">(User-defined window size)</text>
  <text x="520" y="690" text-anchor="middle" font-family="Arial" font-size="10" fill="#6c757d">(PID or proportional control)</text>
</svg>
```

![alt text](Project4_CircuitDiagram.drawio.svg)
```
```
```
```
