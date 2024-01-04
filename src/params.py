import configparser

parameters = {
    "Initial Conditions": {
        "time_sim_duration": {
            "tag": None,
            "size": 1,
            "value": [1000],
            "minmax": [0, 10000],
            "unit": "seconds",
            "tip": "Simulation time",
        },
        "mass_rocket_dry": {
            "tag": None,
            "size": 1,
            "value": [1000],
            "minmax": [0, 10000],
            "unit": "kg",
            "tip": "Rocket Dry Mass",
        },
        "mass_rocket_prop": {
            "tag": None,
            "size": 1,
            "value": [1000],
            "minmax": [0, 10000],
            "unit": "kg",
            "tip": "Rocket Propellant Mass",
        },
        "pos_start": {
            "tag": None,
            "size": 3,
            "value": [0, 0, 0],
            "minmax": [-1000, 1000],
            "unit": "m",
            "tip": "Initial Start Position (x,y,z)",
        },
        "pos_end": {
            "tag": None,
            "size": 3,
            "value": [300, 100, 0],
            "minmax": [-1000, 1000],
            "unit": "m",
            "tip": "Target End Position (x,y,z)",
        },
        "angle_rocket_start": {
            "tag": None,
            "size": 3,
            "value": [0, 90, 0],
            "minmax": [0, 360],
            "unit": "deg",
            "tip": "Rocket Initial Attitude Angle (r,p,y)",
        },
    },
    "State Variables": {},
    "Assets": {},
}


def main():
    global parameters

    params = parameters

    config = configparser.ConfigParser()

    for section, options in params.items():
        config[section] = options

    with open("config/params.ini", "w") as configfile:
        config.write(configfile)


if __name__ == "__main__":
    main()
