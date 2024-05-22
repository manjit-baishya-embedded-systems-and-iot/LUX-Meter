#------------------------------------------------------------------#
#----------------------Initializing UART---------------------------#
import machine
import _thread
import time

# create a UART object
uart = machine.UART(2, 115200)

# shared data storage
uart_data = None

def read_uart():
    global uart_data
    while True:
        data = uart.readline()
        if data:
            data = data.decode('UTF-8').replace('\r\n', '')
            uart_data = data.split(',')
        time.sleep(0.1)  # add a small delay to prevent excessive CPU usage

# start UART reading thread
_thread.start_new_thread(read_uart, ())

#------------------------------------------------------------------#
#----------------------HTTP Server Setup---------------------------#
import usocket as socket
import ujson

def handle_request(client_socket):
    request = client_socket.recv(1024).decode('utf-8')
    print("Received request:")
    print(request)

    # use the latest UART data
    if uart_data and len(uart_data) == 2:
        json_response = ujson.dumps({'value1': uart_data[0], 'value2': uart_data[1]})
    else:
        json_response = ujson.dumps({'error': 'No valid data'})

    # send HTTP response with CORS header
    html_response = f"""HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n\r\n{json_response}"""
    client_socket.send(html_response.encode('utf-8'))
    client_socket.close()

# set up server
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(('192.168.1.45', 80))
server_socket.listen(1)

print("Server started")

# main loop
while True:
    # wait for incoming connections
    client_socket, addr = server_socket.accept()
    print("Client connected:", addr)
    
    # handle incoming requests
    handle_request(client_socket)

#------------------------------------------------------------------#