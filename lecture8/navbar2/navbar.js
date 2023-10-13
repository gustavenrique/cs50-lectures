const toggleBtn = document.querySelector(".toggle-button")
const navLinks = document.querySelector('.navbar ul')

document.addEventListener('DOMContentLoaded', function() {
    toggleBtn.addEventListener('click', function() {
    navLinks.classList.toggle('active')
    })    
})

