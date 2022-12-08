from typing import NoReturn

class _AssertNeverDummy:
    def __bool__(self) -> NoReturn:
        ...

never = _AssertNeverDummy()