document.addEventListener('DOMContentLoaded', function() {
    // For the navbar/toggle button
    const toggleBtn = document.querySelector('.toggle-button')
    const navLinks = document.querySelector('.navbar ul')
    
    toggleBtn.addEventListener('click', function() {
        navLinks.classList.toggle('display-block')
    })
    
})