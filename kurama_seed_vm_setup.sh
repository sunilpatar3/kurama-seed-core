#!/bin/bash
echo "[Kurama Seed Setup Started]"

# Install dependencies
sudo apt update && sudo apt install -y git curl wget unzip nano

# Clone repo if not already
cd ~/Desktop
if [ ! -d "seed-core" ]; then
  git clone https://github.com/sunilpatar3/kurama-seed-core.git seed-core
fi

cd seed-core

# Start Kurama Telegram Agent (requires next file below)
echo "Launching Kurama Telegram AI..."
chmod +x kurama_telegram_responder.py
python3 kurama_telegram_responder.py &
