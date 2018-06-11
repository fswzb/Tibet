#coding:utf-8

USE_GEVENT = False

def use_gevent():
    global USE_GEVENT
    if not USE_GEVENT:
        from gevent import monkey
        monkey.patch_all()
        USE_GEVENT = True


