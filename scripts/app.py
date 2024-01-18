from ui_params import *
from ui_viewport import *
from sim import *
from params import parameters
import threading


import time


class MainApplication:
    def __init__(self, opts):
        print("app constructor")

        self.opts = opts

        # check if INI file exists
        self.params = parameters

        # self.view_ui = ViewportUI(self.opts, self.params)
        # self.view_ui.view.viewer.show()
        # pg.exec()

        self.new_view_ui: Viewport
        # self.view_ui_thread = threading.Thread(target=self.init_view_ui)
        # self.view_ui_thread.start()
        # self.view_ui_thread.join()

        self.new_view_ui = ViewportUI(self.opts, self.params)
        # self.new_view_ui.view.viewer.show()

        self.param_ui = ParameterUI(self.opts, self.params)

        self.simulation = Simulator(self.new_view_ui, self.params)

        self.time = time.perf_counter_ns()

    def init_view_ui(self):
        self.new_view_ui = ViewportUI(self.opts, self.params)
        # self.new_view_ui.view.viewer.show()
        # pg.exec()

    def update(self):
        timeNow = time.perf_counter_ns()
        timeElapsed = (timeNow - self.time) / 1000000000
        self.simulation.process(timeElapsed)

        if self.opts["show_metrics"] == True:
            print(f"[INFO] timeElapsed: {timeElapsed}secs")

        self.time = timeNow

    def run(self):
        t = QtCore.QTimer()  # Create a QTimer
        t.timeout.connect(
            self.update
        )  # Connect the update function to the timeout signal
        t.start(
            self.opts["update_ms"]
        )  # Start the timer with a timeout of 50 milliseconds

        # pg.exec()
        self.param_ui.start_event_loop()
