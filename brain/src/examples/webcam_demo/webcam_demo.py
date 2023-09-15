# requires numpy
import cv2

cap = cv2.VideoCapture("http://10.0.0.78:8080/video")

while(True):
    ret, frame = cap.read()
    cv2.imshow('webcam',frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
