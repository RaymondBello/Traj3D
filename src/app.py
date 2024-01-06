from ui_param import *
from ui_viewport import *
from sim import *
from params import parameters

import time


class MainApplication:
    def __init__(self, opts):
        print("app constructor")

        self.opts = opts

        # check if INI file exists
        self.params = parameters

        self.param_ui = ParameterUI(self.opts)
        self.param_ui.create_window(self.params)

        self.view_ui = ViewportUI(self.opts, self.params)
        self.view_ui.view.viewer.show()
        self.simulation = Simulator(self.view_ui, self.params)

        self.time = time.perf_counter_ns()

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
        dpg.start_dearpygui()
        dpg.destroy_context()

        # pg.exec()
