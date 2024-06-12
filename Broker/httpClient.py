import requests


class HTTPClient:
    def __init__(self, url):
        self._url = url

    def get(self, params=None):
        response = requests.get(self._url, params=params)
        print(f"Response received from Arduino: {response}")
