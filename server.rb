/#########
  *csv write to file as it recives data
        - put into array
        - place that as one line in csv
        - clear array
  *plots the data after file has been updated
#########/
require 'socket'
require 'csv'

server = TCPServer.new 23923
ary = Array.new()
#people = CSV.read('test.csv')

puts time
# setup while loop to write from client
#client = server.accept    # Wait for a client to connect
loop do
  Thread.start(server.accept) do |client|
    sock_domain, remote_port, remote_hostname, remote_ip = client.peeraddr
    puts "connection coming from #{remote_ip} and port #{remote_port}"
    loop do
    line = client.gets.chomp
      ary.push(line)
        # open file to write and creat header
      CSV.open('myfile.csv', 'w',:write_headers=> true,
        :headers => ["PhoneNumber","chem Data","gps(North South)","gps(East Wes\
t)"] #< column header
        ) do |csv_object|

      ary.each {|x| csv_object << x.split(",")}
      client.puts "Hello !"
      client.puts "Time is #{Time.now}"

       end # csv open
    end #loop do
  end #clients connect
end #loop do