nmcli connection add type wifi con-name "REDE" ifname wlan0 ssid "REDE" wifi-sec.key-mgmt wpa-psk wifi-sec.psk "SENHA" 
nmcli connection up "REDE"
