FROM python:3.11-rc-alpine3.16
WORKDIR /api/
ADD . /api/
RUN pip install -U --trusted-host pypi.python.org -r requirements.txt
CMD ["flask", "run", "--host", "0.0.0.0"]