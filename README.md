# BouncyBallSimulator
This is a simple C++ project using SFML to simulate randomly colored bouncy balls with random velocities / gravity values in a small window.

Do what you want with the code. I plan to add various features when I feel like it.

This is one of my first projects outside of university in C++. Please be harsh on my code and if you see anything that merits changes or clarification, and especially any bad code / style, PLEASE reach out to me and give feedback so I can learn from this project. Thank you in advance!

## 🎮 Controls
🖱️ **Left Click** → Spawn a new ball at your mouse location  

## 📦 Installation & Running
### **Download ZIP**
Simply download the zip, unzip it, and then run 
```sh
make
./ball_sim
```
### **Clone the Repository**
```sh
git clone https://github.com/mangokip/BouncyBalls.git
cd BouncyBalls 

make
./ball_sim

```
## Planned Features:
1. MAYBE maximum ball count on screen so I can add collision
2. More creative animations for wall collision
3. Different ball "materials" with designated texture files but still random colors
4. UI additions / cleanup
5. Friction toggle / other physics

## Finished Features:
1. Particles on collision
2. UI for clearing balls, toggling gravity, increasing/decreasing ball speed
   
## Demo Images
-- No Gravity -- 
![Alt text](images/nogravity.png)
-- Gravity --
![Alt text](images/gravity.png)

