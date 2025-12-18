#!/bin/bash
set -e

# ========= COLORS =========
RED='\033[1;31m'
GREEN='\033[1;32m'
YELLOW='\033[1;33m'
BLUE='\033[1;34m'
CYAN='\033[1;36m'
WHITE='\033[1;37m'
RESET='\033[0m'

# ========= PATHS =========
INSTALL_DIR="$HOME/.local/bin"
PROJECT_NAME="MONITOR"

# ========= HEADER =========
clear
echo -e "${CYAN}"
cat << "EOF"
╔════════════════════════════════════════════╗
║   TERMINAL SYSTEM MONITOR INSTALLER        ║
║        Minimal • Fast • Written in C      ║
╚════════════════════════════════════════════╝
EOF
echo -e "${RESET}"

# ========= SYSTEM CHECK =========
echo -e "${BLUE}[*] Checking system dependencies...${RESET}"

missing=0
for cmd in gcc make; do
    if ! command -v "$cmd" >/dev/null 2>&1; then
        echo -e "${RED}[✗] Missing dependency:${RESET} $cmd"
        missing=1
    else
        echo -e "${GREEN}[✓] Found:${RESET} $cmd"
    fi
done

if [ "$missing" -eq 1 ]; then
    echo -e "\n${RED}Installation aborted due to missing dependencies.${RESET}"
    exit 1
fi

# ========= GENMON CHECK  =========
echo -e "\n${BLUE}[*] Checking optional XFCE Genmon support...${RESET}"
if command -v xfce4-genmon-plugin >/dev/null 2>&1; then
    echo -e "${GREEN}[✓] Genmon plugin detected${RESET}"
else
    echo -e "${YELLOW}[!] Genmon plugin not found${RESET}"
    echo -e "${WHITE}    → Panel integration will not be available${RESET}"
    echo -e "${WHITE}    → You can install it later if using XFCE${RESET}"
fi

# ========= BUILD =========
echo -e "\n${BLUE}[*] Building project...${RESET}"
make

# ========= INSTALL =========
echo -e "\n${BLUE}[*] Installing binary...${RESET}"
mkdir -p "$INSTALL_DIR"
make install

# ========= CLEAN =========
echo -e "\n${BLUE}[*] Cleaning build artifacts...${RESET}"
make clean

# ========= PATH CHECK =========
echo -e "\n${BLUE}[*] Verifying PATH...${RESET}"
if ! echo "$PATH" | grep -q "$INSTALL_DIR"; then
    echo -e "${YELLOW}[!] $INSTALL_DIR is not in PATH${RESET}"
    echo -e "${WHITE}Add this to your shell config:${RESET}"
    echo -e "${CYAN}export PATH=\"\$HOME/.local/bin:\$PATH\"${RESET}"
else
    echo -e "${GREEN}[✓] PATH correctly configured${RESET}"
fi

# ========= README.md =========
echo -e "\n${GREEN}══════════════════════════════════════════${RESET}"
echo -e "${GREEN}✓ Installation complete${RESET}"
echo -e "${GREEN}══════════════════════════════════════════${RESET}"

echo -e "\n${WHITE}Usage:${RESET}"
echo -e "  ${CYAN}▶ Run manually:${RESET} ${PROJECT_NAME}"
echo -e "  ${CYAN}▶ XFCE Genmon command:${RESET} ~/.local/bin/${PROJECT_NAME}"

echo -e "\n${BLUE}Happy hacking.${RESET}"

