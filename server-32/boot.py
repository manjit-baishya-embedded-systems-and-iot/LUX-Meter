#------------------------------------------------------------------#
#--------------------Clearing the terminal-------------------------#
import sys

def clear_terminal():
    sys.stdout.write("\033[2J\033[H")

#------------------------------------------------------------------#
#------------------Printing welcome message------------------------#

def print_welcome_message():
    
    # clearing the terminal before starting
    clear_terminal()

    # print welcome message
    print("++++++++++++++++++++++++++++++++++++++++++++")
    print("-------------Starting ESP-32----------------")
    print("++++++++++++++++++++++++++++++++++++++++++++")

#------------------------------------------------------------------#
#----------------------Connecting to WIFI--------------------------#
import network
import time

print_welcome_message()

def connect_to_wifi(ssid, password, static_ip=None):
    wlan = network.WLAN(network.STA_IF)
    wlan.active(True)
    wlan.connect(ssid, password)
    
    print('Connecting to network...')
    
    # Wait for the connection to establish
    while not wlan.isconnected():
        print('Waiting for connection...')
        time.sleep(1)
    
    if static_ip:
        wlan.ifconfig(static_ip)
        print('Network connected at static IP: http://', static_ip[0])
    else:
        IP_address = wlan.ifconfig()
        print('Network connected at dynamic IP: http://', IP_address[0])

# Replace these with your actual WiFi credentials
ssid = 'HOME'
password = 'BSNL_wifi@2569'
desired_ip = ('192.168.1.45', '255.255.255.0', '192.168.1.1', '8.8.8.8')

print_welcome_message()
connect_to_wifi(ssid, password, desired_ip)
print("++++++++++++++++++++++++++++++++++++++++++++")

#-------------------------------------------------------------------------#