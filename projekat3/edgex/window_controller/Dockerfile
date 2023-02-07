FROM python:3.11-rc-alpine3.16
WORKDIR /app/
ADD . /app/
RUN pip install -U --trusted-host pypi.python.org -r requirements.txt
ENTRYPOINT ["python", "./windowController.py"]