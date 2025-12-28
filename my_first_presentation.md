---
marp: true
theme: default
class: center, middle

# Welcome to Marp!
### Your Journey to Beautiful Presentations Starts Here
---
<!-- _class: invert -->
# What is Marp?

- **Markdown Presentation Ecosystem**
- Create slides from plain Markdown
- Simple, fast, and powerful

---

# Why Use Marp?

- Easy to learn
- Version control friendly
- Customizable with CSS
- Export to HTML, PDF, PPTX

---
<!-- _class: invert -->
# Basic Syntax 1

## Headings 2

You should now see your Markdown content rendered as a beautiful slideshow in a side panel. 
>As you make changes to your Markdown, the preview will update instantly.

    Text
### H3

#### H4

##### H5

###### H6

Text

---

## Lists

- Unordered List Item 1
- Unordered List Item 2
  - Nested Item

1. Ordered List Item 1
2. Ordered List Item 2

---

## Images

![Marp Logo](https://marp.app/assets/marp.svg)

---

## Code Blocks

```python
def hello_marp():
    print("Hello, Marp!")
hello_marp()
```

---

### Enhancing Your Marp Presentations: Advanced Tips

Marp offers several directives and features to make your presentations even more dynamic and visually appealing.

#### 1. Global Directives

Place these at the very top of your Markdown file, between the initial `---` markers.

>Example:
```markdown
---
marp: true
theme: gaia
size: 16:9
paginate: true
backgroundColor: #f0f8ff
---

# My Themed Presentation
```
---

#### 2. Local Directives (Per-Slide)

You can apply directives to individual slides by placing them at the beginning of the slide content, after the --- separator.

- `_class: lead`: Apply a CSS class to a specific slide (e.g., for larger text).
- `_backgroundColor: purple`: Override the background color for a single slide.
- `_backgroundImage: url('another-image.png')`: Override the background image.
- `_header: My Section`: Add a header to a slide (appears on subsequent slides until changed).
- `_footer: Confidential`: Add a footer to a slide.

---
<!-- _class: invert -->
>Example:

```markdown
---
marp: true
theme: default
---

# Introduction
---
_class: lead
_backgroundColor: #ffe0b2
# Key Point
This slide has a larger font and a custom background color.
---
_header: Section 1
_footer: Page 2
## Details Here
```

---

#### 3. Custom CSS Themes

For ultimate control over your presentation’s appearance, you can create your own CSS themes.
- Create a CSS file, e.g., my_custom_theme.css.
- Define your styles within this file. Marp uses specific CSS variables and selectors. Refer to Marp’s official documentation for detailed theming guidelines.
>Tip: Inspect the elements of Marp’s default themes (default.css, gaia.css, uncover.css in the Marp VS Code extension directory) to understand their structure.
---
- In your Markdown file, specify your custom theme:

```markdown
---
marp: true
theme: @my_custom_theme.css
---

# Using Custom Theme
```

    Note: You might need to specify the full path if the CSS file is not 
    in the same directory or configured otherwise.

.

    Note: You might need to specify the full path if the CSS file is not in the same directory or configured otherwise.

---

<!-- _footer: Confidential -->
<!-- _backgroundColor: #ffe0b2 -->

[This is a comment that will be hidden.]: #
    Taip nedirba
_footer: Confidential
_backgroundColor: #ffe0b2

> :warning: **Warning:** Do not push the big red button.

> :memo: **Note:** Sunrises are beautiful.

> :bulb: **Tip:** Remember to appreciate the little things in life.

> :calendar: **Calendar:** Remember to appreciate the little things in life.

> :star: :star2: :exclamation: :question:

[žr. čia](https://www.markdownguide.org/hacks/)

---

term
: definition

== Highlight text ==

$\alpha$

---
<!-- _class: invert -->
## Status

```diff
-Latest official release is version 2017a, published on 2017-02-28. 
+Latest official release is version 2017b, published on 2017-03-20.
```

---
 ## Usage
 
```diff 
 | Official version | Our corresponding semver version |
 | ---------------- | -------------------------------- |
+| `2017b`          | `2017.1`                         |
 | `2017a`          | `2017.0`                         |

