import http.client

conn = http.client.HTTPConnection("localhost")
payload = ''
headers = {}
path = 'a' * 10000  # Tried to trigger a buffer overflow, but unsuccessful
conn.request("GET", path, payload, headers)
res = conn.getresponse()
data = res.read()
print(data.decode("utf-8"))
