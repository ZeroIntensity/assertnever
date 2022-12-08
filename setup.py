from setuptools import Extension, setup

with open("./README.md") as f:
    long_desc: str = f.read()

if __name__ == "__main__":
    setup(
        name="assertnever",
        description="Syntactical sugar for assert never.",
        version="1.0.0",
        license="MIT",
        project_urls={
            "Source": "https://github.com/ZeroIntensity/assertnever",
        },
        ext_modules=[Extension("an", ["an.c"])],
        package_data={'an': ['py.typed', '*.pyi']},
    )