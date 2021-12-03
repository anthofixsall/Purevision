



commade gst :

gst-launch-1.0 -v v4l2src device=/dev/video0 num-buffers=-1 ! video/x-raw, width=640, height=480 ! videoconvert ! jpegenc ! rtpjpegpay ! multiudpsink clients=127.0.0.1:5000,127.0.0.1:5001 auto-multicast=true
